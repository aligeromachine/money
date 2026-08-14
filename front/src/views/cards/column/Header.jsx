import React from 'react';
import { CFormCheck } from '@coreui/react';
import { handleDeleteRow } from '../../../components/action/Action';
import { deleteCardsRow, getCardsRow } from '../../../services/cards/request';
import { useModalContent } from '../../../components/hook/ModalContext';
import { ChangeStatusEnable } from '../callback';
import st from '../../../scss/column/row.module.css';

export const columnsTbl = () => {
    const { openModal } = useModalContent();
    const openWithEdit = async id => {
        await getCardsRow(id);
        openModal();
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
            accessorKey: 'title',
            header: 'Title',
        },
        {
            accessorKey: 'amount',
            header: 'Amount',
        },
        {
            accessorKey: 'number',
            header: 'Number',
        },
        {
            accessorKey: null,
            header: 'на Доске',
            cell: ({ row }) => (
                <CFormCheck
                    type="checkbox"
                    checked={row.original.checked}
                    readOnly
                    onClick={() => ChangeStatusEnable({ checked: !row.original.checked, pk: row.original.id })}
                />
            ),
        },
        {
            accessorKey: null,
            header: 'Action',
            cell: ({ row }) => (
                <span>
                    <i onClick={() => handleDeleteRow(row.original.id, deleteCardsRow)}>
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
