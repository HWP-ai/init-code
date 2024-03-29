;;=========================================================
;;
;; Collected By dist1.tech/init-code at 2019-12-17
;;
;; Find On: http://git.savannah.gnu.org/cgit/emacs.git/commit/?id=47bdd84a0a9d20aab934482a64b84d0db63e7532
;;
;; Commit Message: Initial revision
;;
;;=========================================================

;;; StudlyCaps (tm)(r)(c)(xxx)

(defun studlify-region (begin end)
  "Studlify-case the region"
  (interactive "*r")
  (save-excursion
    (goto-char begin)
    (setq begin (point))
    (while (and (<= (point) end)
		(not (looking-at "\\W*\\'")))
      (forward-word 1)
      (backward-word 1)
      (setq begin (max (point) begin))
      (forward-word 1)
      (let ((offset 0)
	    (word-end (min (point) end))
	    c)
	(goto-char begin)
	(while (< (point) word-end)
	  (setq offset (+ offset (following-char)))
	  (forward-char 1))
	(setq offset (+ offset (following-char)))
	(goto-char begin)
	(while (< (point) word-end)
	  (setq c (following-char))
	  (if (and (= (% (+ c offset) 4) 2)
		   (let ((ch (following-char)))
		     (or (and (>= ch ?a) (<= ch ?z))
			 (and (>= ch ?A) (<= ch ?Z)))))
	      (progn
		(delete-char 1)
		(insert (logxor c ? ))))
	  (forward-char 1))
	(setq begin (point))))))

(defun studlify-word (count)
  "Studlify-case the current word, or COUNT words if given an argument"
  (interactive "*p")
  (let ((begin (point)) end rb re)
    (forward-word count)
    (setq end (point))
    (setq rb (min begin end) re (max begin end))
    (studlify-region rb re)))

(defun studlify-buffer ()
  "Studlify-case the current buffer"
  (interactive "*")
  (studlify-region (point-min) (point-max)))
