import { postRequestCheck } from '../../utils/requests';
import { store } from '../store';
import { setRowState, setRowPk } from '../utils/row/state';
import { URL, CmdType } from '../const';
import { getProdTable } from './state';

export const addProdRow = async () => {
    const { pk, formData } = store.getState().rowReducer;
    const params = {
        command: pk === 0 ? CmdType.add : CmdType.edit,
        pk,
        ...formData,
    };
    const response = await postRequestCheck(URL.products, params);
    if (!response) return Promise.reject('Error response');
    await store.dispatch(getProdTable());
    return response;
};

export const deleteProdRow = async pk => {
    const params = {
        command: CmdType.delete,
        pk,
    };
    await postRequestCheck(URL.products, params);
    await store.dispatch(getProdTable());
};

export const getProdRow = async pk => {
    const params = {
        command: CmdType.row,
        pk,
    };
    const response = await postRequestCheck(URL.products, params);
    store.dispatch(setRowPk(pk));
    store.dispatch(setRowState(response));
};
