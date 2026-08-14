import React from 'react';
import { BasicTable } from '../../components/table/BasicTable';
import { columnsTbl } from './column/Header';
import { useEffect } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { getShopTable, setOffset } from '../../services/shop/state';

export const Table = () => {
    const dispatch = useDispatch();
    useEffect(() => {
        dispatch(getShopTable());
    }, [dispatch]);

    const st = useSelector(store => store.shopReducer);

    async function onOffset(value) {
        dispatch(setOffset({ offset: value }));
        dispatch(getShopTable());
    }
    return (
        <BasicTable
            columns={columnsTbl()}
            onOffset={onOffset}
            data={st.draw}
            total={st.recordsTotal}
            limit={st.recordsDisplay}
            offset={st.offset}
        />
    );
};
