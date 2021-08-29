import React from 'react';
import AppBar from '@material-ui/core/AppBar';
import CameraIcon from '@material-ui/icons/PhotoCamera';
import CssBaseline from '@material-ui/core/CssBaseline';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import { makeStyles } from '@material-ui/core/styles';
import Link from '@material-ui/core/Link';
import Button from '@material-ui/core/Button';

export const Header = () => {

    const useStyles = makeStyles((theme) => ({
        icon: {
            marginRight: theme.spacing(2),
        },
        link: {
            margin: theme.spacing(1, 1.5),
          },
          appBar: {
            borderBottom: `1px solid ${theme.palette.divider}`,
          },
          toolbar: {
            flexWrap: 'wrap',
          },
          toolbarTitle: {
            flexGrow: 1,
          },
    }));

    const classes = useStyles();

    return (
        <div>
            <CssBaseline />
            <AppBar position="static" color="default" elevation={0} className={classes.appBar} >
                <Toolbar className={classes.toolbar}>
                    <CameraIcon className={classes.icon} />
                    <Typography variant="h6" color="inherit" noWrap className={classes.toolbarTitle}>
                        Album layout
                    </Typography>
                    <nav>

                    

                        <Link variant="button" color="inherit" href="#" className={classes.link}>
                            Features
                        </Link>
                        <Link variant="button" color="inherit" href="#" className={classes.link}>
                            Enterprise
                        </Link>
                        <Link variant="button" color="inherit" href="#" className={classes.link}>
                            Support
                        </Link>
                    </nav>
                    <Button href="#" color="primary" variant="outlined" className={classes.link}>
                        Login
                    </Button>
                </Toolbar>
            </AppBar>
        </div>

    )

}