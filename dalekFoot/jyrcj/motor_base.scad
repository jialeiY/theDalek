
$fn=20;

module base() {

translate([0, 10, 0])
rotate([90, 0, 0])
linear_extrude(20)
polygon([[-15,0], [15,0], [7.5, 15], [-7.5, 15]]);

}

module screw() {

cylinder(100, 1.6, 1.6, true);
cylinder(1, 3, 1.5);
}

difference() {
base();
union() {
translate([0, 5, 0]) screw();
translate([0, -5, 0]) screw();
}
}