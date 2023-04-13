const express = require('express');
const router = express.Router();

router.get('/',(req,res,next)=>{
    res.status(200).json({
        message:'handling  get request to /products'
    });
});

router.post('/',(req,res,next)=>{
    res.status(200).json({
        message:'handling post request to /products'
    });
});

router.get('/:productId',(req,res,next)=>{
    const id = req.params.productId;
    if(id==='special')
    {
        res.status(200).json({
            message:'you have encountered special product',
            id:id
        });
    }
    else{
        res.status(200).json({
            message:'it is just a normal product'
        });
    }
});

router.patch('/:productId',(req,res,next)=>{
    const id = req.params.productId;
    res.status(200).json({
        message:'patching request for a product',
        id: id
    }) ;
});

router.delete('/:productId',(req,res,next)=>{
    const id = req.params.productId;
    res.status(200).json({
        message:'recieved a delete request for a product',
        id: id
    }) ;
});

module.exports = router;