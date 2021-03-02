$("#cam_up").click(function(){
    $.post("/index/cam-motor", {move:"up"})
});

$("#cam_down").click(function(){
    $.post("/index/cam-motor", {move:"down"})
});