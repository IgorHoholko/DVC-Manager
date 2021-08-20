import React, {useState} from 'react';
import Button from '@material-ui/core/Button';

const Counter = () => {
    const [count, setCount] = useState(0);

    function increment() {
        setCount(count + 1)
    }

    function decrement() {
        setCount(count - 1)
    }
    return (
        <div>
            <h1>{count}</h1>
            <Button onClick={increment} variant="contained" color="primary">Increment</Button>
            <Button onClick={decrement} variant="contained" color="primary">Decrement</Button>
        </div>
    )
}

export default Counter