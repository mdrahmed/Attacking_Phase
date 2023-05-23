// intercept.js
Interceptor.attach(Module.findExportByName(null, 'isConditionFalse'), {
    onEnter: function (args) {
        console.log("Intercepted isConditionFalse() function");
        args[0] = ptr(1);  // Change the condition to true
    }
});

