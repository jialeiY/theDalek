$("#cam_up").click(function(){
    $.post("/cam-motor", {move:"up"})
});

$("#cam_down").click(function(){
    $.post("/cam-motor", {move:"down"})
});

$("#car_forward").click(function(){
    $.post("/car-motor", {move:"forward"})
});
$("#car_backward").click(function(){
    $.post("/car-motor", {move:"backward"})
});
$("#car_left").click(function(){
    $.post("/car-motor", {move:"left"})
});
$("#car_forward").click(function(){
    $.post("/car-right", {move:"right"})
});




$("#add_face").click(function(){
    console.log("add")
    $.post("/faces", {face_name:$("#face_name").val()})
});