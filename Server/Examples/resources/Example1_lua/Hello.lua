local inst = testClass();
inst:setPosition(1, 1, 1);
inst:setPosition(2.0, 2.0, 2.0);
inst:setPosition3(3.0, 3.0, 3.0);


collectgarbage();
inst = nil;

