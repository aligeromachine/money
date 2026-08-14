from pydantic import BaseModel
from api.back.model import MainModel

LOG_ALL: str = 'all'

class LogMessage(MainModel):
    pass

class LogSignal(BaseModel):
    message: str | dict
    data: str = "ok"


class LogAllSignal(BaseModel):
    money: str
    api: str
    auth: str
    libs: str
    machine: str
    django: str
