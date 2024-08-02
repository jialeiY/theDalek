
module rounded_board(height, width, depth) {
    x = width / 2 - 5 ;
    y = depth / 2 - 5;
    hull() {
    translate([x, y, height/2]) cylinder(5, 5, height, true);
    translate([-x, y, height/2]) cylinder(5, 5, height, true);
    translate([x, -y, height/2]) cylinder(5, 5, height, true);
    translate([-x, -y, height/2]) cylinder(5, 5, height, true);
    }
}

module boxFR(){
    translate([30, 35, 0] )cube([50, 100, 100]);
}


module wheelFR() {
    translate([35, 70, 30]) rotate([0, 90, 0]) cylinder(40, 30, 30);
}

module robot() {
difference() {
translate([0, 0, 30]) rounded_board(5, 150, 200);
union() {
boxFR(); mirror([1, 0, 0]) boxFR();
mirror([0,1,0]){boxFR(); mirror([1, 0, 0]) boxFR();}
}
}

wheelFR(); mirror([1, 0, 0]) wheelFR();
mirror([0,1,0]){wheelFR(); mirror([1, 0, 0]) wheelFR();}

translate([0, 8, 50])cube([80, 90, 50], true);
translate([0, 0, 80]) cylinder(20, 30, 30, true);
translate([0, 50, 50])rotate([-90, 0, 0])cylinder(50,30,0);
}



scale([0.001, 0.001, 0.001]) rotate([-90, 0, 0]) rotate([0, 0, -90]) robot();