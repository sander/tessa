
function helloworld()
	print("Hello world!");
end

services:create("TestPlugin/HelloWorld", helloworld);

services:create("TestPlugin/GoodbyeWorld", function () print("Goodbye, world...") end);

