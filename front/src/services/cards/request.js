import { setRowState, setRowPk } from '../utils/row/state';
import { store } from '../store';
import { postRequestCheck } from '../../utils/requests';
import { getCardsTable } from './state';
import { URL, CmdType } from '../const';

export const addCardsRow = async () => {
    const { pk, formData } = store.getState().rowReducer;
    const params = {
        command: pk === 0 ? CmdType.add : CmdType.edit,
        pk,
        ...formData,
    };
    const response = await postRequestCheck(URL.cards, params);
    if (!response) return Promise.reject('Error response');
    await store.dispatch(getCardsTable());
    return response;
};

export const deleteCardsRow = async pk => {
    const params = {
        command: CmdType.delete,
        pk,
    };
    await postRequestCheck(URL.cards, params);
    await store.dispatch(getCardsTable());
};

export const getCardsRow = async pk => {
    const params = {
        command: CmdType.row,
        pk,
    };
    const response = await postRequestCheck(URL.cards, params);
    store.dispatch(setRowPk(pk));
    store.dispatch(setRowState(response));
};

export const setCardEnableStatus = async (checked, pk) => {
    const params = {
        command: CmdType.enable,
        pk,
        checked,
    };
    const response = await postRequestCheck(URL.cards, params);
    if (!response) return Promise.reject('Error response');
    await store.dispatch(getCardsTable());
    return response;
};
