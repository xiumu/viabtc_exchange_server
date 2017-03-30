/*
 * Description: 
 *     History: yang@haipo.me, 2017/03/16, create
 */

# ifndef _ME_MARKET_H_
# define _ME_MARKET_H_

# include "me_config.h"

# define MARKET_ORDER_TYPE_LIMIT    1
# define MARKET_ORDER_TYPE_MARKET   2

# define MARKET_ORDER_SIDE_ASK      1
# define MARKET_ORDER_SIDE_BID      2

typedef struct order_t {
    uint64_t        id;
    uint32_t        type;
    uint32_t        side;
    double          create_time;
    double          update_time;
    char            *market_name;
    uint32_t        user_id;
    mpd_t           *price;
    mpd_t           *amount;
    mpd_t           *fee_rate;
    mpd_t           *left;
    mpd_t           *freeze;
    mpd_t           *deal_stock;
    mpd_t           *deal_money;
    mpd_t           *deal_fee;
} order_t;

typedef struct market_t {
    char            *name;
    char            *stock;
    char            *money;
    int             stock_prec;
    int             money_prec;
    int             fee_prec;
    dict_t          *orders;
    dict_t          *users;
    dict_t          *volumes;
    skiplist_t      *asks;
    skiplist_t      *bids;

    nw_timer        timer;
    uint64_t        id_start;
    mpd_t           *volumes_24hour;
    time_t          volumes_update;
} market_t;

market_t *market_create(struct market *conf);

int market_put_limit_order(market_t *m, uint32_t user_id, uint32_t side, mpd_t *amount, mpd_t *price, mpd_t *fee_rate);
int market_put_market_order(market_t *m, uint32_t user_id, uint32_t side, mpd_t *amount, mpd_t *fee_rate);

list_t *market_get_order_list(market_t *m, uint32_t user_id);
order_t *market_get_order(market_t *m, uint64_t id);
void market_cancel_order(market_t *m, order_t *order);
mpd_t *market_get_volumes(market_t *m);

# endif

