local inst = testClass();
inst.setPosition(1.0, 1.0, 1.0);
inst.setPosition(2.0, 2.0, 2.0);
inst.setPosition3(3.0, 3.0, 3.0);
inst = null;
collectgarbage();