from datetime import datetime, timedelta, date
from decimal import Decimal
import logging
from typing import Self
from pydantic import BaseModel, Field, model_validator
from api.back.model import AmountSelector, BaseMessage, KeyValue
from libs.validate.exp import validate_list_conv
from libs.dt.utils import time_parse

logger = logging.getLogger(__name__)

class SearchParams(BaseModel):
    startDate: datetime | str | None = None
    endDate: datetime | str | None = None
    groupTypeProd: list[KeyValue] | str | None = None
    groupOrganization: list[KeyValue] | str | None = None
    prim: str | None = None

    @model_validator(mode='after')
    def complete_search(self) -> Self:

        if isinstance(self.startDate, str):
            dt: datetime | None = time_parse(raw=self.startDate)
            if dt:
                self.startDate = dt

        if isinstance(self.endDate, str):
            dt: datetime | None = time_parse(raw=self.endDate)
            if dt:
                self.endDate = dt + timedelta(days=1)

        if isinstance(self.groupTypeProd, str):
            raw: list[KeyValue] | None = validate_list_conv(response=self.groupTypeProd, Model=KeyValue)
            if raw:
                self.groupTypeProd = raw

        if isinstance(self.groupOrganization, str):
            raw: list[KeyValue] | None = validate_list_conv(response=self.groupOrganization, Model=KeyValue)
            if raw:
                self.groupOrganization = raw

        return self

class SearchMessage(BaseMessage):
    amount: Decimal = Decimal(0)
    shop: int = 0
    prod: int = 0
    form_data: dict | SearchParams | None = None

    @model_validator(mode='after')
    def complete_message(self) -> Self:
        if isinstance(self.form_data, dict) and self.form_data:
            self.form_data = SearchParams(**self.form_data)
        return self


class SearcSelector(AmountSelector):
    shop: str
    cat: str
    prod: str
    base_dt: date

class TableSelector(BaseModel):
    total: int = Field(..., alias="amount_sum")
    days_count: int = Field(..., alias="amount_len")
