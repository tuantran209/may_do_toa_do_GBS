require('dotenv').config();
const express = require('express')
const mongoose = require('mongoose')
const cors = require('cors');
const opn = require('opn');
const productRoute = require('./routes/productRoute');
const bodyParser = require('body-parser');
const app = express()



const MONGO_URL= process.env.MONGO_URL
const PORT = process.env.PORT || 3000
const FRONTEND = process.env.FRONTEND
const urlen = bodyParser.urlencoded({extended: false});

const corsOptions = {
  origin: FRONTEND,
  credentials:true,     
  optionsSuccessStatus: 200 
}

const ipserver = '118.71.173.86';    
const portserver = '8282';           

var str = "http://" + ipserver + ":" + portserver + "/login";

opn(str);
app.set("view engine","ejs");
app.set("views","./views");
app.use(cors());
app.use(express.json());
app.use(bodyParser.json());
app.use(express.urlencoded({extended: false }))
app.use('/',productRoute);
app.use(express.static('views'));


mongoose.set("strictQuery",false)
mongoose.
connect(MONGO_URL)
.then(()=>{
  console.log('connect to mongoDB');
 
  app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`)
    
  });
}).catch((error)=>{
  console.log(error);
})