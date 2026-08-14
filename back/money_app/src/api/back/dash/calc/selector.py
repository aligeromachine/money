from decimal import Decimal
from django.db.models import Sum
from money.models import Buy, Cards, Profit
from api.back.dash.calc.model_func import CardSelector, CardsAgg, SelectorBuy, SelectorProf
from api.back.dash.calc.query import CALC_BUY_TOTAL, CALC_PROF_TOTAL, SQL_ORDER_CARDS

def get_top_user_cards(user_id: int) -> CardsAgg:
    payload = [CardSelector.from_orm(it) for it in Cards.objects.raw(raw_query=SQL_ORDER_CARDS, params=[user_id])]
    cards: CardsAgg = CardsAgg.from_raw_array(payload)
    return cards

def get_stat_buy(user_id: int) -> list[SelectorBuy]:
    return [SelectorBuy.from_orm(it) for it in Buy.objects.raw(raw_query=CALC_BUY_TOTAL, params=[user_id])]

def get_stat_prof(user_id: int) -> list[SelectorProf]:
    return [SelectorProf.from_orm(it) for it in Profit.objects.raw(raw_query=CALC_PROF_TOTAL, params=[user_id])]

def get_user_total_cards_amount(user_id: int) -> Decimal:
    total: Decimal = Cards.objects.filter(user_id=user_id).aggregate(total=Sum('amount'))['total'] or Decimal(0)
    return total
