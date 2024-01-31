const Product = require('../models/productModels');
const User = require('../models/userModels');
const axios = require('axios');


async function getAddressFromCoordinates(lat, lon) {
  try {
    const response = await axios.get(`https://nominatim.openstreetmap.org/reverse?format=json&lat=${lat}&lon=${lon}`);
    return response.data.display_name;
  } catch (error) {
    console.error(error);
  }
}

var IsLogin = false;
var CurrentUserName = null;


function calculateDistance(lat1, lon1, lat2, lon2) {
  const R = 6371; 
  const dLat = toRadians(lat2 - lat1);
  const dLon = toRadians(lon2 - lon1);
  const a = Math.sin(dLat / 2) * Math.sin(dLat / 2) + Math.cos(toRadians(lat1)) * Math.cos(toRadians(lat2)) * Math.sin(dLon / 2) * Math.sin(dLon / 2);
  const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
  const distance = R * c; 
  return distance;
}
function toRadians(degrees) {
  return degrees * (Math.PI / 180);
}


const renderLogin = async(req,res) =>{ 
  try {
    IsLogin = false;
    
     res.render('login',{check : null});
  } catch (error) {
     res.status(500).json({ message: error.message });
 
  }
 }


  const login = async(req,res)=>{  
    try {

      IsLogin = false;
      CurrentUserName = null;
        const user = await User.find();
        var p1 = req.body.param1;
        var p2 = req.body.param2;

        const filteredUser = user.filter((item) => {
         return item.username == p1 && item.password == p2;
       });
       if(filteredUser.length == 1){
        IsLogin = true;
        CurrentUserName = p1;
        res.redirect('/bangchinh');
       }
       else{
        IsLogin = false;
        res.render('login',{check : 0});
       }

    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };
  const postdata = async(req,res) => {
    try {

        const tmp = req.body;
        
        await getAddressFromCoordinates(parseFloat(tmp.coordinatesDevice.latitude), parseFloat(tmp.coordinatesDevice.longtitude)).then(async (diachi) => {
           tmp.diachi = diachi;
        });

        const product = await Product.create(tmp);

        var lat1 = parseFloat(product.coordinatesDevice.latitude);
        var long1= parseFloat(product.coordinatesDevice.longtitude);
        var lat2 = parseFloat(product.coordinatesGateway.latitude);
        var long2 = parseFloat(product.coordinatesGateway.longtitude);
        let caldistance = calculateDistance(lat1, long1, lat2, long2);

        await Product.updateMany({ iddevice: product.iddevice }, { distance : caldistance.toFixed(5)*1000 });

        res.status(200).json(product);    

      
    } catch (error) {
      console.log(error.message);
      res.status(500).json({message: error.message})
    }
  };
  const idthietbi = async(req,res)=>{
    try {

        
        
        const product = await Product.find();
        const param1 = parseFloat(req.query.param1); 
        const filteredProducts = product.filter((item) => {
          return item.iddevice == param1;
        });
        res.render('idthietbi', { filteredProducts });
      
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };
  const thoigian = async(req,res)=>{
    try {
        const product = await Product.find();
        var p1 = req.query.param1;
        var p2 = req.query.param2;
        const filteredProducts = product.filter((item) => {
         return item.date.ngaythangnam == p1 && item.date.giophutgiay ==p2;
       });
      res.render('thoigian', { filteredProducts });
      
        
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };
  const toadothietbi = async(req,res)=>{
    try {
      if(IsLogin==true){
        const product = await Product.find();
      var param1 = req.query.param1; 
      var param2 = req.query.param2;
      const filteredProducts = product.filter((item) => {
        return  item.coordinatesDevice.latitude == param1 && 
                item.coordinatesDevice.longtitude==param2;
      });
      res.render('toadothietbi', { filteredProducts });
      }
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };
  const toadogateway = async(req,res)=>{
    try {
      if(IsLogin == true){
        const product = await Product.find();
        var param1 = req.query.param1; 
        var param2 = req.query.param2;
        const filteredProducts = product.filter((item) => {
        return item.coordinatesGateway.latitude == param1 && 
              item.coordinatesGateway.longtitude==param2;
      });
      res.render('toadogateway', { filteredProducts });
      }
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };
  const khoangcach = async(req,res)=>{
    try {
      if(IsLogin == true){
        const product = await Product.find();
        var param1 = req.query.param1; 
        var param2 = req.query.param2;
        const filteredProducts = product.filter((item) => {
        return item.distance >=parseFloat(param1) && item.distance <= parseFloat(param2);
      });
      res.render('khoangcach', { filteredProducts });
      }
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };
  const diachi = async(req,res)=>{
    try {
      if(IsLogin==true){
        const product = await Product.find();
        var param1 = req.query.param1; 
        var param2 = req.query.param2;
        const filteredProducts = product.filter((item) => {
        return item.diachi.includes(param1,0) || item.diachi.includes(param2,0);
      });
      res.render('diachi', { filteredProducts });
      }
      
    } catch (error) {
      res.status(500).json({ message: error.message });
    }
  };
const map = async (req, res) => {
  try {
    if(IsLogin==true){
      res.render('map');
    }
    } catch (error) {
    res.status(500).json({ message: error.message });
    }
}

const jsonForMap = async(req,res) =>{
  try {
    if(IsLogin==true){
      const product = await Product.find();
      res.status(200).json({ product});
    }
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
}
const bangchinh = async(req,res) => {
  try {
    const filteredProducts = await Product.find();
    res.render('bangchinh',{filteredProducts});
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
}




const getSignUp = async(req,res)=>{
  try {
    res.render('createacc',{result : null});
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
}

const postSignUp = async(req,res) =>{                                  
  try {
    
    var KhongTrungLap = false;
    var MatKhauKhongKhop = false;
    var MatKhauManh = false;
    const user = await User.find();
    var param1 =  req.body.param1;
    var param2 =  req.body.param2;
    var param3 =  req.body.param3;
    var param4 = req.body.param4;

    if(param3 != param4){
      MatKhauKhongKhop = true;
    }

    if(/\d/.test(param3) && param3.match(/[A-Z]/) ){
      MatKhauManh = true;
    }

    const filteredUser = user.filter((item) => {
      return item.username == param1 || item.email == param2 ;
    });
    if(filteredUser.length==0 && param1.length != 0 && param2.length !=0 && param3.length !=0 && MatKhauKhongKhop == false && MatKhauManh)
    {
      KhongTrungLap = true;
      const newUser = new User({
        username : param1,
        email : param2,
        password : param3,
      });
      User.create(newUser);
    }
    
    if(MatKhauManh==false){
      res.render('createacc',{result : "matkhauyeu"});
    }
    else if(MatKhauKhongKhop){
      res.render('createacc',{result : "khongkhop"});
    }
    else if(KhongTrungLap==false){
      res.render('createacc',{result : "chuataoduoc"});
    }
    else if(KhongTrungLap){
      res.render('createacc',{result : "dataoduoc"});
    }

  } catch (error) {
    res.status(500).json({ message: error.message });
  }


}

 const getChangePassword = async(req,res)=>{
  try {
    res.render('changePassword',{result : null});
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
}


const ChangePassword = async(req,res) =>{
  try {
    var MatKhauManh = false;
    var param1 =  req.body.param1;
    var param2 =  req.body.param2;
    var MatKhauKhongKhop = false;
    if(param1 !=param2) MatKhauKhongKhop = true;

    if(/\d/.test(param1) && param1.match(/[A-Z]/) ) MatKhauManh = true;
    

    if(MatKhauKhongKhop){
      res.render('changePassword',{result : "khongkhop"});
    }
    else if(MatKhauManh==false){
      res.render('changePassword',{result : "matkhauyeu"});
    }
    else{
      await User.findOneAndUpdate({ username: CurrentUserName }, { password: param1 });
      res.render('changePassword',{result : "dadoimatkhau"});
    }
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
}

 


  module.exports  = {
    postdata,
    idthietbi,
    thoigian,
    toadothietbi,
    toadogateway,
    khoangcach,
    diachi,
    map, jsonForMap,bangchinh,

    login,getSignUp,postSignUp,renderLogin,ChangePassword,getChangePassword
  }