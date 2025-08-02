
unsafe extern "C" {
    unsafe fn c_from_rs();
    unsafe fn cc_from_rs();
    unsafe fn mod_from_rs();
}

pub fn run() {
    println!("Hello Rust");

    unsafe {
        c_from_rs();
        cc_from_rs();
        mod_from_rs();
    }
}
