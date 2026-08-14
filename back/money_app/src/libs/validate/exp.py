from typing import Any
import orjson
from pydantic import ValidationError
import logging
from libs.const import CONST
from libs.types.exp import TModel, TStr

logger = logging.getLogger(__name__)

def to_json(data: dict | list, prn: bool = False) -> Any:
    if not data:
        return None

    try:
        return orjson.dumps(data).decode('utf-8')
    except Exception as e:
        if prn: 
            logger.error(f'{str(e)}, {data=}')
        return None

def to_json_pretty(data: dict | list, prn: bool = False) -> str:
    if not data:
        return str(CONST.empty)

    try:
        json_bytes = orjson.dumps(data, option=orjson.OPT_INDENT_2)
        json_string = json_bytes.decode()
        return str(json_string)
    except Exception as e:
        if prn: 
            logger.error(f'{str(e)}, {data=}')
        return str(CONST.empty)

def validate_conv(response: TStr, prn: bool = False) -> Any:
    if not response:
        return None

    try: 
        return orjson.loads(response)
    except Exception as e:
        if prn: 
            logger.error(f'{str(e)}, {response=}')
        return None

def validate_dict(response: dict | None, Model: TModel, prn: bool = True) -> TModel | None:
    if not response:
        return None
    if not isinstance(response, dict):
        return None

    try:
        if not isinstance(Model, type):
            raise TypeError("model must be a class, not an instance")
        return Model(**response)
    except ValidationError as e:
        if prn: 
            logger.error(f'{str(e)}, {response=}, {Model=}')
        return None

def validate_list(response: list, Model: TModel, prn: bool = True) -> list[TModel] | None:
    if not response:
        return None
    if not isinstance(response, list):
        return None

    try:
        if not isinstance(Model, type):
            raise TypeError("model must be a class, not an instance")
        return [Model(**it) for it in response]
    except ValidationError as e:
        if prn: 
            logger.error(f'{str(e)}, {response=}, {Model=}')
        return None

def validate_dict_conv(response: TStr, Model: TModel, prn: bool = True) -> TModel | None:
    if not response:
        return None

    try: 
        return validate_dict(response=orjson.loads(response), Model=Model, prn=False)
    except Exception as e:
        if prn: 
            logger.error(f'{str(e)}, {response=}, {Model=}')
        return None

def validate_list_conv(response: TStr, Model: TModel, prn: bool = True) -> list[TModel] | None:
    if not response:
        return None

    try: 
        return validate_list(response=orjson.loads(response), Model=Model, prn=False)
    except Exception as e:
        if prn: 
            logger.error(f'{str(e)}, {response=}, {Model=}')
        return None

def validate_dict_list(response: dict, Model: TModel, key: str, prn: bool = True) -> list[TModel] | None:
    if key not in response:
        return None

    try:
        sub = response[key]
        return validate_list(response=sub, Model=Model, prn=False)
    except Exception as e:
        if prn: 
            logger.error(f'{str(e)}, {response=}, {Model=}')
        return None

def validate_str(response: bytes, prn: bool = True) -> str | None:
    if not response:
        return None

    if not isinstance(response, bytes):
        return None

    try:
        return response.decode()
    except Exception as e:
        if prn: 
            logger.error(f'{str(e)}, {response=}')
        return None
