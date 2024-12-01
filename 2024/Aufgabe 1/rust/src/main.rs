use std::fs::read_to_string;

fn read_lines(filename: &str) -> Vec<i32> {
    read_to_string(filename) 
        .unwrap()  // panic on possible file-reading errors
        .lines()  // split the string into an iterator of string slices
        .flat_map(|s| s.split_whitespace())
        .filter_map(|num| num.parse::<i32>().ok())  // make each slice into a string
        .collect()  // gather them together into a vector
}

fn task1(a_input : &Vec<i32>, b_input : &Vec<i32>) {

    let a_length = a_input.len();
    let b_length = b_input.len();
    let mut sum  = 0; 
    if a_length == b_length {
         
        for n  in 0..a_length {
            let mut interim_result= a_input[n] - b_input[n];

            if interim_result < 0 {
                interim_result *= -1;
            }
            sum += interim_result; 
        }
    }

    println!("Task1: {}", sum)
}

fn task2(a_input : &Vec<i32>, b_input : &Vec<i32>) {

    let a_length = a_input.len();
    let b_length = b_input.len();
    let mut sum  = 0; 
        
        for n  in 0..a_length {
            let mut interim_result =0;
            for t in 0..b_length {
                if a_input[n] == b_input[t] {
                    interim_result += 1; 
                }
            }
            interim_result = interim_result * a_input[n]; 
            sum += interim_result; 
        }


    println!("Task2: {}", sum)
}

fn main() {
    
    let input = read_lines("./input.txt");

    //Get 2 Lists 
    let mut a_input : Vec<i32> = vec![];
    let mut b_input : Vec<i32> = vec![]; 

    let length = input.len();
    let mut i = 0; 
    while i < length {
        a_input.push(input[i]);
        b_input.push(input[i+1]);
        i += 2; 
    }

    a_input.sort();
    b_input.sort();

    task1(&a_input, &b_input);
    task2(&a_input, &b_input);
    
}
