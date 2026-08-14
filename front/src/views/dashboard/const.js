const DEFAUL_CARD = {
    title: "__",
    amount: 0
}

const DEFAUL_CARDS = {
    one: DEFAUL_CARD,
    two: DEFAUL_CARD,
    three: DEFAUL_CARD
}

export const DEFAUL_DASH = {
    capital: {cash: 0, cards: 0, year: 0},
    cards: DEFAUL_CARDS,
    profit: {year: 0, month: 0, week: 0, day: 0},
    buy: {year: 0, month: 0, week: 0, day: 0},
    daily: [],
    shop: []
};
