import java.util.*;
import java.io.*;
import java.net.*;

class Start {
  public static void main(String[] theArrayOfString) {
    String url = "http://www.compiletimeerror.com/2013/08/java-downloadextract-all-images-from.html";
    Map<String,Set<String>> images = (new ImagesWebFinder()).getImages(url);
    
    for (String extension : images.keySet()) {
      System.out.println("\n -------------- ." + extension + " --------------\n");
      
      for (String imageName : images.get(extension))
        System.out.println(imageName);
    }
  }
}

/*
 -------------- .jpg --------------

https://cf.dropboxstatic.com/static/images/index/animation-strips/hero-intro-bg-vflMdtS9d.jpg
https://cf.dropboxstatic.com/static/images/index/animation-strips/hero-loop-bg-vflsg8hml.jpg

 -------------- . --------------

https://dropbox.com/hstsping

 -------------- .gif --------------

https://cf.dropboxstatic.com/static/images/icons/icon_spacer-vflN3BYt2.gif
https://cf.dropboxstatic.com/static/images/icons/ajax-loading-small-vfl3Wt7C_.gif

 -------------- .png --------------

https://cf.dropboxstatic.com/static/images/index/shared_folders-vflOiYxu8.png
https://cf.dropboxstatic.com/static/images/index/animation-strips/static-images/send-videos-quickly-vflhWvqHj.png
https://cf.dropboxstatic.com/static/images/index/file_recovery-vfldsGm-1.png
https://cf.dropboxstatic.com/static/images/index/animation-strips/static-images/work-on-slides-together-vfligazGL.png
https://cf.dropboxstatic.com/static/images/index/automatic_updates-vfl5sZs7k.png
https://cf.dropboxstatic.com/static/images/security_keys/insert-vflkCfC4_.png
https://cf.dropboxstatic.com/static/images/index/offline_access-vfl3bndh9.png
https://cf.dropboxstatic.com/static/images/index/preview_and_download-vflY0wjwA.png
https://cf.dropboxstatic.com/static/images/index/any_device-vflAudVJW.png
https://cf.dropboxstatic.com/static/images/index/organization-vflB3ImJo.png
https://cf.dropboxstatic.com/static/images/index/animation-strips/static-images/docs-anywhere-vflA67DXc.png
https://cf.dropboxstatic.com/static/images/index/large_files-vflv7R_Vc.png
https://cf.dropboxstatic.com/static/images/index/simple_sharing-vfl6GdL6B.png
https://www.dropbox.com/static/images/logo.png
https://cf.dropboxstatic.com/static/images/index/all_your_files-vflH9BpRk.png
https://cf.dropboxstatic.com/static/images/index/automatic_backup-vfl_WNwPR.png
https://cf.dropboxstatic.com/static/images/index/animation-strips/static-images/keep-your-photos-safe-vflZe9PHC.png
https://cf.dropboxstatic.com/static/images/index/animation-strips/static-images/never-lose-a-file-again-vfleR0in4.png
https://cf.dropboxstatic.com/static/images/index/sec-verification-vflzoigzY.png
https://cf.dropboxstatic.com/static/images/index/animation-strips/posters/hero-poster-vfl1gZOAd.png
*/