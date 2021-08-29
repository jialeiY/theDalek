$("#cam_up").click(function(){
    $.post("/cam-motor", {move:"up"})
});

$("#cam_down").click(function(){
    $.post("/cam-motor", {move:"down"})
});

$("#car_forward").click(function(){
    $.post("/car-motor", {move:"move_forward"})
});
$("#car_backward").click(function(){
    $.post("/car-motor", {move:"move_backward"})
});
$("#car_left").click(function(){
    $.post("/car-motor", {move:"move_left"})
});
$("#car_right").click(function(){
    $.post("/car-motor", {move:"move_right"})
});




$("#add_face").click(function(){
    console.log("add")
    $.post("/faces", {face_name:$("#face_name").val()})
});