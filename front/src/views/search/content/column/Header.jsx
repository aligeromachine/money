import React from 'react';
import { handleDeleteRow } from '../../../../components/action/Action';
import { deleteSearchRow, getSearchRow } from '../../../../services/search/request';
import { useSearchContent } from '../../../../components/hook/SearchContext';
import st from '../../../../scss/column/row.module.css';

export const columnsTbl = () => {
    const { openModal } = useSearchContent();
    const openWithEdit = async id => {
        const response = await getSearchRow(id);
        openModal({pk: id, ...response});
    };

    return [
        {
            accessorKey: 'id',
            header: 'Id',
            size: 100,
        },
        {
            accessorKey: 'created',
            header: 'Created',
        },
        {
            accessorKey: 'shop',
            header: 'Shop',
        },
        {
            accessorKey: 'cat',
            header: 'Catalog',
        },
        {
            accessorKey: 'prod',
            header: 'Prod',
        },
        {
            accessorKey: 'amount',
            header: 'Amount',
        },
        {
            accessorKey: 'title',
            header: 'Title',
        },
        {
            accessorKey: null,
            header: 'Action',
            cell: ({ row }) => (
                <span>
                    <i onClick={() => handleDeleteRow(row.original.id, deleteSearchRow)}>
                        <img className={st.iconMl} src={'/static/img/delete.png'} height={24} width={24} />
                    </i>

                    <i onClick={() => openWithEdit(row.original.id)}>
                        <img className={st.iconMl} src={'/static/img/edit.png'} height={24} width={24} />
                    </i>
                </span>
            ),
        },
    ];
};
