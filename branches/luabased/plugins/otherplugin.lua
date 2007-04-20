
services:call("TestPlugin/HelloWorld");

events:subscribe("Events/Plugins/AllLoaded", function () services:call("TestPlugin/GoodbyeWorld"); end);