# Emulate defer from go in C++

## Semantics
Roughly match the semantics of `defer` in go. For more information on
the defer keyword in go, see [the go tour](https://tour.golang.org/flowcontrol/12).

## Usage
1. You can defer a named lambda:

        auto deferred_named_lambda = [](){
            cout << "deferred named lambda." << endl;
        };
        defer(deferred_named_lambda);

1. You can defer an anonymous lambda:

        defer([](){ cout << "deferred anonymous lambda." << endl;});

1. You can defer a function:

        int deferred_function() {
            cout << "deferred function." << endl;
        }
        int main() {
            defer(deferred_function);
        }

## Examples
See example.cpp

## Test
1. `make`
1. `./example`
