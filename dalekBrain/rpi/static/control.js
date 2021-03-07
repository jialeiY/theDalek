$("#cam_up").click(function(){
    $.post("/cam-motor", {move:"up"})
});

$("#cam_down").click(function(){
    $.post("/cam-motor", {move:"down"})
});

$("#add_face").click(function(){
    console.log("add")
    $.post("/faces", {face_name:$("#face_name").val()})
});