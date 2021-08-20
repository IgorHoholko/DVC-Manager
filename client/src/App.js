import axios from "axios";
import React, { useEffect } from "react";

import {
  BrowserRouter as Router,
  Switch,
  Route,
  Link
} from "react-router-dom";
import SignIn from "./pages/SignIn";

export default function App() {
  return (
    <Router>
      <div>
        <nav>
          <ul>
            <li>
              <Link to="/">Home</Link>
            </li>
            <li>
              <Link to="/logout">Logout</Link>
            </li>
            <li>
              <Link to="/login">Login</Link>
            </li>
            <li>
              <Link to="/secret">Secret</Link>
            </li>
          </ul>
        </nav>

        {/* A <Switch> looks through its children <Route>s and
            renders the first one that matches the current URL. */}
        <Switch>
        <Route path="/logout">
            <Logout />
          </Route>
          <Route path="/login">
            <SignIn />
          </Route>
          <Route path="/secret">
            <Secret />
          </Route>
          <Route path="/">
            <Home />
          </Route>
        </Switch>
      </div>
    </Router>
  );
}

function Home() {
  useEffect(() => {
    fetch("/api").then(resp => resp.json()).then(resp => console.log(resp))
  }, [])
  return <h2>Home</h2>;
}

function Logout() {
  useEffect(() => {
    axios.post("/api/auth/logout")
  }, [])
  return <h2>Logout</h2>;
}


function Secret() {
  return <h2>Secret</h2>;
}