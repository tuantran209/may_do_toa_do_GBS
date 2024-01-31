const express = require('express')
const router = express.Router();


const {

    postdata,
    idthietbi,
    thoigian,
    toadothietbi,
    toadogateway,
    khoangcach,
    diachi,
    map,jsonForMap,bangchinh,
    
    login,getSignUp,postSignUp,renderLogin,ChangePassword,getChangePassword
    
    
     } = require('../controllers/productController');

     


router.post("/postdata", postdata);
router.get('/idthietbi', idthietbi);
router.get('/thoigian', thoigian);
router.get('/toadothietbi',toadothietbi);
router.get('/toadogateway',toadogateway);
router.get('/khoangcach',khoangcach);
router.get('/diachi',diachi);
router.get('/map',map);  
router.get('/jsonForMap', jsonForMap);
router.get('/bangchinh',bangchinh);


router.get('/login',renderLogin);
router.post('/login',login);
router.get('/createacc',getSignUp);
router.post('/createacc',postSignUp);
router.get('/changepassword',getChangePassword);
router.post('/changepassword',ChangePassword);

module.exports = router;