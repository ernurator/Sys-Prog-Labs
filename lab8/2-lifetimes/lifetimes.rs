struct List<'a> {
    val: i32,
    next: Option<&'a List<'a>>,
}

#[allow(unused_variables)]
fn main() {
    let my_list = make_list(&1);
}

fn make_list(starting_value: &i32) -> List {
    let list_node_2 = List {
        val: *starting_value + 1,
        next: None,
    };

    let list_node_1 = List {
        val: *starting_value,
        next: Some(&list_node_2),
    };

    return list_node_1;
}
