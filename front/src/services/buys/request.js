import { store } from '../store';
import { setRowState, setRowPk } from '../utils/row/state';
import { postRequestCheck } from '../../utils/requests';
import { URL, CmdType } from '../const';
import { getBuysTable } from './state';

export const addBuyRow = async () => {
    const { pk, formData } = store.getState().rowReducer;
    const params = {
        command: pk === 0 ? CmdType.add : CmdType.edit,
        pk,
        ...formData,
    };
    const response = await postRequestCheck(URL.buy, params);
    if (!response) return Promise.reject('Error response');
    await store.dispatch(getBuysTable());
    return response;
};

export const deleteBuyRow = async pk => {
    const params = {
        command: CmdType.delete,
        pk,
    };
    await postRequestCheck(URL.buy, params);
    await store.dispatch(getBuysTable());
};

export const getBuyRow = async pk => {
    const params = {
        command: CmdType.row,
        pk,
    };
    const response = await postRequestCheck(URL.buy, params);
    store.dispatch(setRowPk(pk));
    store.dispatch(setRowState(response));
};
