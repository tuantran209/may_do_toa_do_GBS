const mongoose = require('mongoose');

const parameters = mongoose.Schema(
    {
        
        iddevice :{
            type : String,
        },
        date :{ 
            type : {
                ngaythangnam :String,
                giophutgiay : String
            }
        },
        coordinatesDevice:{
            type : {
                latitude : String,
                longtitude : String
            }
        },
        coordinatesGateway:{
            type: {
                latitude: String,
                longtitude: String
            }
        },
        distance : {
            type : Number
        },
        diachi:{
            type : String
        },
        bando:{
            type : String
        },
        state:{
            type : Number
        }

    },
    {
        timestamps : true
    }
)


const Product = mongoose.model('Product',parameters);

module.exports = Product;