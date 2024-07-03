$fn=50;

difference() {
cylinder(8+2.5, 6, 6);

union() {
    
intersection() {
cylinder(8, 5.3/2, 5.3/2);
translate([0, 0, 4])
cube([3.8-0.1, 10, 8], true);
}

translate([0, 0, 8])
cylinder(2.5, 2, 2);
}
}