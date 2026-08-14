import React from 'react';
import { BasicTable } from '../../../components/table/BasicTable';
import { columnsTbl } from './column/Header';
import { useEffect } from 'react';
import { useSelector, useDispatch } from 'react-redux';

export const TableSearch = ({st}) => {
    async function onOffset(value) {
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
