from django.http import HttpRequest
import logging
from api.back.decore import validate_model
from api.back.products.model import ProductsMessage
from api.back.products.table import table_prod_data
from api.back.products.base import add_prod_data, delete_prod_row, edit_prod_data, get_prod_row, list_prod_data
from api.back.const import CmdRouter

logger = logging.getLogger(__name__)

@validate_model(ProductsMessage)  # type: ignore
def invoke_response(request: HttpRequest, item: ProductsMessage) -> dict | list:
    respo = dict(data="err", message="undefinded")

    if item.command == CmdRouter.table:
        respo = table_prod_data(item=item)

    if item.command == CmdRouter.add:
        respo = add_prod_data(item=item)

    if item.command == CmdRouter.delete:
        respo = delete_prod_row(item=item)

    if item.command == CmdRouter.row:
        respo = get_prod_row(item=item)

    if item.command == CmdRouter.edit:
        respo = edit_prod_data(item=item)

    if item.command == CmdRouter.listkeys:
        respo = list_prod_data(item=item)

    return respo
