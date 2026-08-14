from typing import ParamSpec, Protocol, Type, TypeAlias, TypeVar
from pydantic import BaseModel


P = ParamSpec("P")
R = TypeVar("R")

class TPModel(Protocol):
    def dump_model(self) -> dict:
        ...


TModel = TypeVar('TModel', bound=BaseModel)
TTModel: TypeAlias = Type[TModel]

TStr: TypeAlias = str | bytes
DictModel: TypeAlias = dict | TModel
DictList: TypeAlias = dict | list
DLModel: TypeAlias = dict | list | TModel
JsonType: TypeAlias = dict | TModel | None

JsonDict: TypeAlias = dict[str, bool | int | str | list | dict]
JsonList: TypeAlias = list[JsonDict | str | int | float | bool]
ResponseRequest: TypeAlias = JsonDict | JsonList | bytes | None
ResponseFunc: TypeAlias = dict | list | bytes | str | int | float | bool | None
