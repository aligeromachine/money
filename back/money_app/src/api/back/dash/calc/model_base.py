from collections import defaultdict
from decimal import Decimal
from datetime import timedelta, date
from typing import Self, TypeVar
from pydantic import BaseModel, model_validator
from api.back.dash.calc.model_func import Capital, CardsAgg, DateRng, SelectorBuy, SelectorProf, TopTitle
from machine.tools.selector import get_list_user_finance
from api.back.dash.calc.selector import get_stat_buy, get_stat_prof, get_top_user_cards, get_user_total_cards_amount
from machine.tools.model import WidgetRange

T = TypeVar('T', bound='ReduceInfo')

class ReduceInfo(BaseModel):
    totalBuy: list[SelectorBuy] = []
    totalProf: list[SelectorProf] = []
    calcWgYears: list[WidgetRange] = []
    cardsTotalAmount: Decimal = Decimal(0)

    capital: Capital = Capital()
    cards: CardsAgg = CardsAgg()
    profit: DateRng = DateRng()
    buy: DateRng = DateRng()

    topDaily: list[TopTitle] = []
    topShop: list[TopTitle] = []

    @model_validator(mode='after')
    def complete(self) -> Self:

        today = date.today()
        startmounth = today - timedelta(days=today.day - 1)
        monday = today - timedelta(days=today.weekday())

        self.buy.year = sum([it.amount for it in self.totalBuy], Decimal(0))
        self.buy.month = sum([it.amount for it in self.totalBuy if it.base_dt >= startmounth], Decimal(0))
        self.buy.week = sum([it.amount for it in self.totalBuy if it.base_dt >= monday], Decimal(0))
        self.buy.day = sum([it.amount for it in self.totalBuy if it.base_dt == today], Decimal(0))

        self.profit.year = sum([it.amount for it in self.totalProf], Decimal(0))
        self.profit.month = sum([it.amount for it in self.totalProf if it.base_dt >= startmounth], Decimal(0))
        self.profit.week = sum([it.amount for it in self.totalProf if it.base_dt >= monday], Decimal(0))
        self.profit.day = sum([it.amount for it in self.totalProf if it.base_dt == today], Decimal(0))

        self.capital.cards = self.cardsTotalAmount

        total_profit = sum([it.profit for it in self.calcWgYears], Decimal(0))
        total_buy = sum([it.buy for it in self.calcWgYears], Decimal(0))

        self.capital.year = self.profit.year - self.buy.year
        self.capital.cash = total_profit - total_buy - self.capital.cards

        by_day = defaultdict(Decimal)
        temp = defaultdict(lambda: defaultdict(Decimal))

        records = sorted(self.totalBuy, key=lambda x: x.base_dt, reverse=True)

        for r in records:
            by_day[r.base_dt] += r.amount
            temp[r.base_dt][r.shop] += r.amount

            if len(by_day) > 10 and len(temp) > 10:
                break

        by_shop = [(day, shop, total) for day, shops in temp.items() for shop, total in shops.items()]

        sorted_days = sorted(by_day.items(), reverse=True)
        sorted_shops = sorted(by_shop, key=lambda x: x[0], reverse=True)

        for i in range(min(10, len(sorted_days), len(sorted_shops))):
            day_key, day_val = sorted_days[i]
            self.topDaily.append(TopTitle(title=day_key, amount=day_val))
            _, shop_key, shop_val = sorted_shops[i]
            self.topShop.append(TopTitle(title=shop_key, amount=shop_val))

        return self

    @classmethod
    def load_from_db(cls: type[T], user_id: int) -> T:
        raw: dict = dict(
            totalBuy=get_stat_buy(user_id=user_id),
            totalProf=get_stat_prof(user_id=user_id),
            calcWgYears=get_list_user_finance(user_id=user_id),
            cardsTotalAmount=get_user_total_cards_amount(user_id=user_id), 
            cards=get_top_user_cards(user_id=user_id),
        )
        return cls(**raw)
