// 
// Build project for emscripten
// Run using:
// node make.js [-f FILE, --file=FILE, --makefile=FILE] [target]
//

var target = "Release";//"DEBUG";

for (var i=2;i<process.argv.length;i++){
    if (process.argv[i].indexOf('-')===0){
        i++;
    } else  if (i === process.argv.length-1){
        target = process.argv[i];
    }
}

var project = {
    "options": [(target=="debug"?"-O0":"-O3"), "-Werror"/*, "-s USE_SDL=2"*/],
    "buildoptions": ["-std=c++11", "-stdlib=libc++", "-fno-exceptions"],
    "defines": ["GLM_FORCE_RADIANS",(target=="debug"?"DEBUG":"NDEBUG")],
    "targetdir": "../planfloor-pages",
    "target": "index.html",
    "includedirs": [ "../kick/src", "../kick/libs/include" ,"./src"],
	"files":[ {
            "root":"../kick/",
            "filter":"src/.*\\.cpp"
        },
        {
            "root":"./src/",
            "filter":".*.cpp"}],
    "embed":[
	{
            "root":"../kick/",
            "filter":"assets/shaders/\\.*"
	},
        {
            "root":".",
            "filter":"planfloor-assets/models/.*"
        },
        {
            "root":"../kick/",
            "filter":"assets/font/.*\\.fnt"
        },
        {
            "root":"../kick/",
            "filter":"assets/ui/.*\\.txt"
        },
        {
            "root":".",
            "filter":"planfloor-assets/shaders/.*glsl"
        },
        {
            "root":".",
            "filter":"planfloor-assets/shaders/.*shader"
        }],
    "preload":[
        {
            "root":"../kick",
            "filter":"assets/textures/\\.*"
        },
        {
            "root":"../kick",
            "filter":"assets/ui/\\.*png"
        },
        {
            "root":"../kick",
            "filter":"assets/font/.*\\.png"
        },
        {
            "root":"../kick",
            "filter":"assets/ui/.*\\.png"
        },
        {
            "root":".",
            "filter":"planfloor-assets/textures/.*\\.png"
        }
    ]
};

module.exports = project;
