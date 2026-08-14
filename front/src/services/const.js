export const URL = {
    dash: '/dash/',
    buy: '/buy/',
    cards: '/cards/',
    cat: '/catalog/',
    products: '/products/',
    profit: '/profit/',
    shop: '/shop/',
    source: '/source/',
    log: '/logger/',
    search: '/search/',
    version: '/version/',
    auth: {
        register: '/auth/register/',
        login: '/auth/login/',
        refresh: '/auth/refresh/',
        protected: '/auth/protected/',
        logout: '/auth/logout/',
        change: '/auth/change/',
    },
};
export const CmdType = {
    add: 'add_data',
    edit: 'edit_data',
    delete: 'delete_row',
    row: 'get_row',
    table: 'table_data',
    enable: 'state_enable',
    listkeys: 'list_keys',
    info: 'info',
};
export const STATE = {
    base: {
        recordsTotal: 0,
        offset: 0,
        recordsDisplay: 100,
        draw: [],
        loading: 'loading' | 'idle' | 'failed',
    },
    row: {
        pk: 0,
        formData: {},
    },
    bar: {
        sidebarShow: true,
        sidebarUnfoldable: false,
        theme: 'light',
    },
    register: {
        register: false,
        error: '',
        loading: 'empty',
    },
    token: {
        loading: 'empty',
    },
};
