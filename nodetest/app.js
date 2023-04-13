const express = require('express');
const morgan = require('morgan');
const productsroute = require('./api/routes/product');
const ordersroute = require('./api/routes/orders');
const app = express();
app.use(morgan('dev'));
app.use('/products',productsroute);
app.use('/orders',ordersroute);
app.use((req,res,next)=>{
    const error = new Error('invalid request');
    error.status=404;
    next(error);
});
app.use((error,req,res,next)=>{
    res.status(error.status || 500);
    res.json({
        error:{
            message: error.message 
        }
    });
});
/*app.use((req,res,next)=>{
    res.status(200).json({
        message:'it works'
    });
});
*/

module.exports = app;