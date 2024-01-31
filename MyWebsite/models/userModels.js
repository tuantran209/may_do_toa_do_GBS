const mongoose = require('mongoose');

const paramuser = mongoose.Schema(
    {
        username : {
            type : String,
        },
        password : {
            type : String,
        },
        email :{
            type : String,
        }
        
    },
    {
        timestamps : true
    }
)
const User = mongoose.model('User',paramuser);

module.exports = User;