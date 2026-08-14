import { postRequestCheck } from '../../utils/requests';
import { store } from '../store';
import { setRowState, setRowPk } from '../utils/row/state';
import { URL, CmdType } from '../const';
import { getShopTable } from './state';

export const addShopRow = async () => {
    const { pk, formData } = store.getState().rowReducer;
    const params = {
        command: pk === 0 ? CmdType.add : CmdType.edit,
        pk,
        ...formData,
    };
    const response = await postRequestCheck(URL.shop, params);
    if (!response) return Promise.reject('Error response');
    await store.dispatch(getShopTable());
    return response;
};

export const deleteShopRow = async pk => {
    const params = {
        command: CmdType.delete,
        pk,
    };
    await postRequestCheck(URL.shop, params);
    await store.dispatch(getShopTable());
};

export const getShopRow = async pk => {
    const params = {
        command: CmdType.row,
        pk,
    };
    const response = await postRequestCheck(URL.shop, params);
    store.dispatch(setRowPk(pk));
    store.dispatch(setRowState(response));
};
