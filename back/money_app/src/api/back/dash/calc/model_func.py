from datetime import date
from decimal import Decimal
from typing import Self
from pydantic import BaseModel, model_validator
from libs.const import CONST
from libs.math.exp import trim_decimal
from libs.model.exp import BaseModelWithRawArray

class DateRng(BaseModel):
    year: Decimal = Decimal(0)
    month: Decimal = Decimal(0)
    week: Decimal = Decimal(0)
    day: Decimal = Decimal(0)

    @model_validator(mode='after')
    def complete(self) -> Self:
        self.year = trim_decimal(self.year)
        self.month = trim_decimal(self.month)
        self.week = trim_decimal(self.week)
        self.day = trim_decimal(self.day)
        return self

class Capital(BaseModel):
    cash: Decimal = Decimal(0)
    cards: Decimal = Decimal(0)
    year: Decimal = Decimal(0)

    @model_validator(mode='after')
    def complete(self) -> Self:
        self.cash = trim_decimal(self.cash)
        self.cards = trim_decimal(self.cards)
        self.year = trim_decimal(self.year)
        return self

class CardSelector(BaseModelWithRawArray):
    title: str = CONST.empty
    amount: Decimal = Decimal(0)

    @model_validator(mode='after')
    def complete(self) -> Self:
        self.amount = trim_decimal(self.amount)
        return self

class CardsAgg(BaseModelWithRawArray):
    one: CardSelector = CardSelector()
    two: CardSelector = CardSelector()
    three: CardSelector = CardSelector()

class TopTitle(BaseModel):
    title: str | date
    amount: Decimal = Decimal(0)

    @model_validator(mode='after')
    def complete(self) -> Self:
        self.amount = trim_decimal(self.amount)
        if isinstance(self.title, date):
            self.title = self.title.strftime('%d-%m-%Y')
        return self

class SelectorStat(BaseModelWithRawArray):
    id: int
    base_dt: date
    title: str
    amount: Decimal

    @model_validator(mode='after')
    def base_selector(self) -> Self:
        self.amount = trim_decimal(self.amount)
        return self

class SelectorBuy(SelectorStat):
    shop: str
    cat: str
    prod: str

class SelectorProf(SelectorStat):
    source: str
