import React, { useEffect } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { BasicTable } from '../../components/table/BasicTable';

import { getCatTable, setOffset } from '../../services/catalog/state';
import { columnsTbl } from './column/HeaderCat';

export const TableCat = () => {
    const dispatch = useDispatch();
    useEffect(() => {
        dispatch(getCatTable());
    }, [dispatch]);

    const st = useSelector(store => store.catalogReducer);

    async function onOffset(value) {
        dispatch(setOffset({ offset: value }));
        dispatch(getCatTable());
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
