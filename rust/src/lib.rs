extern crate libc;
use libc::uint32_t;

#[no_mangle]
pub extern fn add(a: uint32_t, b: uint32_t) -> uint32_t {
    a + b
}
