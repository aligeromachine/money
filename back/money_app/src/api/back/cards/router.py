from django.http import HttpRequest
from api.back.decore import validate_model
from api.back.cards.model import CardsMessage
from api.back.cards.table import table_cards_data
from api.back.cards.base import add_cards_data, delete_cards_row, edit_cards_data, enable_cards_state, get_cards_row
from api.back.const import CmdRouter

@validate_model(CardsMessage)  # type: ignore
def invoke_response(request: HttpRequest, item: CardsMessage) -> dict | list:
    respo = dict(data="err", message="undefinded")

    if item.command == CmdRouter.table:
        respo = table_cards_data(item=item)

    if item.command == CmdRouter.add:
        respo = add_cards_data(item=item)

    if item.command == CmdRouter.edit:
        respo = edit_cards_data(item=item)

    if item.command == CmdRouter.delete:
        respo = delete_cards_row(item=item)

    if item.command == CmdRouter.row:
        respo = get_cards_row(item=item)

    if item.command == CmdRouter.enable:
        respo = enable_cards_state(item=item)

    return respo
