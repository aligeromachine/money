import logging
from functools import wraps
from django.http import HttpRequest
from typing import Any, Callable, Concatenate
from pydantic import BaseModel, ValidationError
from libs.types.exp import DictList, P, TModel
from libs.const import CONST
from libs.validate.exp import validate_dict_conv
from libs.django.jsonResponse import ORJSONResponse

logger = logging.getLogger(__name__)

def parse_api_model(Model: TModel) -> Callable[[Callable[Concatenate[HttpRequest, TModel, P], DictList]], Callable[Concatenate[HttpRequest, P], DictList]]:  # type: ignore
    def decorator(func: Callable[Concatenate[HttpRequest, TModel, P], DictList]) -> Callable[Concatenate[HttpRequest, P], DictList]:  # type: ignore
        @wraps(func)
        def wrapper(request: HttpRequest, *args: P.args, **kwargs: P.kwargs) -> DictList:
            if not request.body:
                return dict(data='err', message='body empty')

            data = validate_dict_conv(response=request.body, Model=Model)
            if data is None:
                return dict(data='err', message='validate Model Error')

            try:
                rv = func(request, data, *args, **kwargs)
                if isinstance(rv, BaseModel):
                    return rv.model_dump()
                return rv
            except ValidationError as e:
                return dict(data='err', message=str(e))
        return wrapper
    return decorator

def token_response(token: dict | None = None, msg: str | None = None, code: int = 200) -> ORJSONResponse:
    return ORJSONResponse(data=dict(token=token, message=msg), status=code)

def check_post(view_func: Callable[..., ORJSONResponse]) -> ORJSONResponse:
    def wrapper_view(request: HttpRequest) -> ORJSONResponse:
        if request.method != CONST.POST:
            return token_response(msg='Method not allowed', code=405)
        return view_func(request)
    return wrapper_view

def validate_auth(Model: TModel) -> ORJSONResponse:
    def decorator(func: Callable[..., ORJSONResponse]) -> ORJSONResponse:
        @wraps(func)
        def wrapper(request: HttpRequest, *args: Any, **kwargs: Any) -> ORJSONResponse:

            data: TModel | None = validate_dict_conv(response=request.body, Model=Model)
            if not data:
                return token_response(msg='Invalid data Model', code=400)
            return func(request, data, *args, **kwargs)
        return wrapper
    return decorator

def draw_paginate(func: Callable[P, dict]) -> Callable[P, dict]:  # type: ignore
    @wraps(func)
    def wrapper(*args: P.args, **kwargs: P.kwargs) -> dict:
        ls, count, offset, limit = func(*args, **kwargs)
        result = dict(
            recordsTotal=count,
            offset=offset,
            recordsDisplay=limit,
            draw=ls
        )
        return result
    return wrapper
