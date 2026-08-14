from pydantic import BaseModel
from libs.model.exp import BaseModelWithRawArray

class Respo(BaseModel):
    data: str
    message: str

class RespoOk(Respo):
    data: str = 'Ok'

class RespoErr(RespoOk):
    data: str = 'Err'

class CalcCountSQL(BaseModelWithRawArray):
    id: int
    value: int
