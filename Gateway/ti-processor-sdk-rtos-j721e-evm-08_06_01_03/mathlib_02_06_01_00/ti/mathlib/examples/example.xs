/* MAIN ROUTINE FROM HERE */
if(arguments.length < 3)
{
  print("USAGE:");
  print("xs -f example.js platform dst delivery_type\n");
  java.lang.System.exit(1);
}
var target=arguments[0];
var dst=arguments[1];
var deltype = arguments[2];
var repositDir = new java.io.File(dst+"/examples");
  if (!(repositDir.exists() && repositDir.isDirectory())) {
    repositDir.mkdirs();
  }
  
  //repositDir = new java.io.File(dst+"/examples/HoughLinesDemo");
  //if (!(repositDir.exists() && repositDir.isDirectory())) {
  //  repositDir.mkdirs();
  //}  
 
/* Copy Common Files */
/* Copy Module */
var copy = xdc.loadCapsule('ti/mas/swtools/Copy.xs');

  copy.File("./examples/package.xdc", dst+"/examples");
  copy.File("./examples/Regression/main.c.xdt", dst+"/examples/Regression");
  
if(target.toString().match("64"))
{
  
  var prjtarget= "64P";
}
else if (target.toString().match("66"))
{
  var prjtarget= "66";
}
else if(target.toString().match("674"))
{
  var prjtarget= "674";
}

var tplt = xdc.loadTemplate('ti/vxlib/examples/Regression/lnk.cmd.xdt');
tplt.genFile (dst+'/examples/Regression/lnk.cmd', null, [target,prjtarget]);

var tplt = xdc.loadTemplate('ti/vxlib/examples/package.bld.xdt');
tplt.genFile (dst+'/examples/package.bld', null, [target,prjtarget,deltype]);

     

