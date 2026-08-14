import { postRequestCheck } from '../../utils/requests';
import { store } from '../store';
import { setRowState, setRowPk } from '../utils/row/state';
import { URL, CmdType } from '../const';
import { getProfitTable } from './state';

export const addProfitRow = async () => {
    const { pk, formData } = store.getState().rowReducer;
    const params = {
        command: pk === 0 ? CmdType.add : CmdType.edit,
        pk,
        ...formData,
    };
    const response = await postRequestCheck(URL.profit, params);
    if (!response) return Promise.reject('Error response');
    await store.dispatch(getProfitTable());
    return response;
};

export const deleteProfitRow = async pk => {
    const params = {
        command: CmdType.delete,
        pk,
    };
    await postRequestCheck(URL.profit, params);
    await store.dispatch(getProfitTable());
};

export const getProfitRow = async pk => {
    const params = {
        command: CmdType.row,
        pk,
    };
    const response = await postRequestCheck(URL.profit, params);
    store.dispatch(setRowPk(pk));
    store.dispatch(setRowState(response));
};
