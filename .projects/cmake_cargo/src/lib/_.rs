
pub fn run() {
    println!("Hello Rust");
}

#[unsafe(no_mangle)]
extern "C" fn rs_from_c() {
    println!("Hello Rust from C");
}


#[unsafe(no_mangle)]
extern "C" fn rs_from_cc() {
    println!("Hello Rust from C++");
}
