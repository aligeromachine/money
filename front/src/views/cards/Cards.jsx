import React from 'react';
import { CCard, CCardBody, CCol, CRow } from '@coreui/react';
import { ModalProvider } from '../../components/hook/ModalContext';
import { Header } from '../../components/elems/Header';
import { Button } from '../../components/elems/Button';
import { Table } from './Table';
import { CardsModal } from './modal/Base';
import { Auth } from '../../components/auth/Auth';

export const DataCards = () => {
    return (
        <Auth>
            <CCard className="mb-4">
                <Header title={'DataCards'} />
                <CCardBody>
                    <ModalProvider>
                        <CardsModal />
                        <Button title={'Add Card'} />
                        <Table />
                    </ModalProvider>
                </CCardBody>
            </CCard>
        </Auth>
    );
};
