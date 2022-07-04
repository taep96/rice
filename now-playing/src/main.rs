use std::process;

fn main() {
    if let Err(e) = now_playing::run() {
        eprintln!("Application error: {}", e);
        process::exit(1);
    }
}
