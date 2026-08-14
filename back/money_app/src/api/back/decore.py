from collections.abc import Callable
from functools import wraps
import logging
from typing import Any
from django.http import HttpRequest
from api.back.model import MainModel
from libs.validate.exp import validate_dict_conv

logger = logging.getLogger(__name__)

def validate_model(Model: type[MainModel]) -> Callable[..., Callable[..., dict | list]]:  # type: ignore
    def decorator(func: Callable[..., dict | list]) -> Callable[..., dict | list]:  # type: ignore
        @wraps(func)
        def wrapper(request: HttpRequest, *args: Any, **kwargs: Any) -> dict | list:
            if not request.body:
                return dict(data='err', message='body empty')
            data: MainModel | None = validate_dict_conv(request.body, Model=Model, prn=True)
            if not data:
                return dict(data='err', message=f'validate_dict_conv: {Model}')
            data.user_id = request.user_id
            rv: dict | list = func(request, data, *args, **kwargs)
            return rv
        return wrapper
    return decorator
